#!/usr/bin/env python
'''
Usage: dbloads.py
Input: list of all database db_filenames, delimited by \0
Output: list of dbLoadRecords(...) calls

Relevant environment variables:
    * DB_PARAMETERS: parameters to pass to dbLoadRecords()
    * QUEUE_SIZE_BASE: the minimum callback queue size
    * QUEUE_SIZE_SCALE: total_records * scale

The callback queue size will be calculated as follows:

    (QUEUE_SIZE_SCALE * total_records) + QUEUE_SIZE_BASE
'''

import os
import sys


def count_number_of_records(db_filename):
    """Count the number of records in `db_filename`."""
    with open(db_filename, 'rt') as f:
        return len(
            [line for line in f.readlines()
             if line.startswith('record(')]
        )


def load_record_entry(db_filename):
    """Format dbLoadRecords() based on env variable DB_PARAMETERS."""
    env = dict(os.environ)
    db_filename = os.path.split(db_filename)[-1]
    env['db_filename'] = db_filename

    return (
        'dbLoadRecords("{db_filename}", "PORT=ASYN_PLC,{DB_PARAMETERS}")'
        ''.format(**env)
    )


def main():
    db_filenames = sys.stdin.read().strip('\0').split('\0')

    if db_filenames:
        total_records = sum(count_number_of_records(fn) for fn in db_filenames)
    else:
        total_records = 0

    # Multiply the number of records by the scale:
    queue_size_scale = int(os.environ.get('QUEUE_SIZE_SCALE', '2'))

    # The minimum size of the queue, outside of those for additional records:
    queue_size_base = int(os.environ.get('QUEUE_SIZE_BASE', '2000'))
    queue_size = queue_size_scale * total_records + queue_size_base

    print('# Total records: {0}'.format(total_records))
    print('callbackSetQueueSize({0})'.format(queue_size))
    print('\n'.join(load_record_entry(fn) for fn in db_filenames))


if __name__ == '__main__':
    main()
