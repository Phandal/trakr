# Trakr

A bespoke time tracking app that is only useful to me.

## Installation
```bash
git clone https://github.com/Phandal/trakr
cd trakr
cmake -S . -B build
cmake --build build
sudo cmake --install build
```

## Usage
```bash
# Show usage message
trakr help

# Clock in to a session with task name
trakr in --task <task-name> [--at <hh:mm>]

# Clock out of the currently active task
trakr out [--at <hh:mm>]

# Report time clocked grouped by task (day defaults to today)
trakr report [--day <yyyy-mm-dd>]

# Update a session
trakr update --id <session-id> [--start <yyyy-mm-dd hh:mm>] [--end <yyyy-mm-dd hh:mm>] [--task <task-name>]

# Delete a session
trakr delete  --id <session-id>
```

## Configuration
Session are saved as plain text and can be easily read and modified by a human. Session files are
stored in `TRAKR_DIR` or `~/.trakr` by default.

## Example task file
```sh
1    |2026-04-19 08:15|2026-04-19 13:30|My custom task
2    |2026-04-19 13:30|2026-04-19 16:45|Another task
...
12532|2026-05-20 12:00|                |A task this is not complete yet
```

## Todo
- [ ] Parse the cli arguments - (use `getopt_long`) and refactor [usage](#usage) to use subcommands.
- [ ] Create a parser for a session
- [ ] Work out saving the session data to a day file
