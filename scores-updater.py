#!/usr/bin/env python3

import github3
from datetime import datetime
from datetime import date
from dateutil import tz
import re
import httplib2
import os

from apiclient import discovery
from oauth2client import client
from oauth2client import tools
from oauth2client.file import Storage
import local_secrets

def parse_solved_tasks(s):
    ids = set()
    for r in re.findall('#([0-9]*)', s):
        ids.add(int(r))
    return ids

try:
    import argparse
    flags = argparse.ArgumentParser(parents=[tools.argparser]).parse_args()
except ImportError:
    flags = None

SCOPES = 'https://www.googleapis.com/auth/spreadsheets'
CLIENT_SECRET_FILE = 'client_secret.json'
APPLICATION_NAME = 'Leetcode marathon status updater'
MARATHON_START_DATE = date(2017, 3, 18)


def get_credentials():
    """Gets valid user credentials from storage.

    If nothing has been stored, or if the stored credentials are invalid,
    the OAuth2 flow is completed to obtain the new credentials.

    Returns:
        Credentials, the obtained credential.
    """
    home_dir = os.path.expanduser('~')
    credential_dir = os.path.join(home_dir, '.credentials')
    if not os.path.exists(credential_dir):
        os.makedirs(credential_dir)
    credential_path = os.path.join(credential_dir,
                                   'sheets.googleapis.com-python-quickstart.json')

    store = Storage(credential_path)
    credentials = store.get()
    if not credentials or credentials.invalid:
        flow = client.flow_from_clientsecrets(CLIENT_SECRET_FILE, SCOPES)
        flow.user_agent = APPLICATION_NAME
        if flags:
            credentials = tools.run_flow(flow, store, flags)
        else: # Needed only for compatibility with Python 2.6
            credentials = tools.run(flow, store)
        print('Storing credentials to ' + credential_path)
    return credentials

def main():
    credentials = get_credentials()
    http = credentials.authorize(httplib2.Http())
    discoveryUrl = ('https://sheets.googleapis.com/$discovery/rest?'
                    'version=v4')
    service = discovery.build('sheets', 'v4', http=http,
                              discoveryServiceUrl=discoveryUrl)

    rangeName = 'Days!B6:I7'
    result = service.spreadsheets().values().get(
        spreadsheetId=local_secrets.SPREADSHEET_ID, range=rangeName).execute()
    values = result.get('values', [])
    assert(len(values) == 2)

    today = datetime.utcnow().date()
    start = datetime(today.year, today.month, today.day, tzinfo=tz.tzutc())
    g = github3.login(local_secrets.USER_NAME, local_secrets.GITHUB_ACCESS_TOKEN)
    solved_today_tasks = []
    print('Participant scores:')
    for i in range(len(values[0])):
        r = g.repository(values[0][i], values[1][i])
        solved_today = set()
        for c in r.commits(since=start):
            solved_today.update(parse_solved_tasks(c.message))
        solved_today_tasks.append(len(solved_today))
        print(values[0][i], len(solved_today))

    print('Updating the table...', end='')
    rowid = (today - MARATHON_START_DATE).days + 8
    rangeTodayTasks = 'Days!B{rowid}:I{rowid}'.format(rowid=rowid)
    values = [
        solved_today_tasks
    ]
    writeBody = {
        'values': values
    }
    result = service.spreadsheets().values().update(
        spreadsheetId=local_secrets.SPREADSHEET_ID, range=rangeTodayTasks,
        valueInputOption='RAW', body=writeBody).execute()
    print('ok!')


if __name__ == '__main__':
    main()
