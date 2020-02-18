'''
Usage: dbloads.py
Input: list of all database db_filenames, delimited by \0
Output: list of dbLoadRecords(...) calls
'''

import os
import sys


def load_record_entry(db_filename):
    db_filename = os.path.split(db_filename)[-1]
    env.update(dict(db_filename=db_filename))

    return (
        'dbLoadRecords("{db_filename}", '
        '"PORT=ASYN_PLC,{DB_PARAMETERS}")'
        ''.format(**env)
    )


db_filenames = sys.stdin.read().strip('\0').split('\0')
env = dict(os.environ)
print('\n'.join(load_record_entry(fn) for fn in db_filenames))
