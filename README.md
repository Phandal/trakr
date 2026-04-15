# Trakr

A bespoke time tracking app that is only useful to me.

## Installation
```bash
git clone https://github.com/Phandal/trakr
cd trakr
cmake -S . -B build
cmake --build build
cmake --install build
```

## Usage
```bash
# Clock in to a session with task name
trakr --in <task-name>

# Clock out of the currently active task
trakr --out

# Report time clocked today grouped by task
trakr --report

# Report time clocked on a specific day grouped by task
trakr --report <yyyy-mm-dd>

# Update a session
trakr --update <session-id> --start <hh:mm> --end <hh:mm> --task <task-name>

# Delete a session
trakr --delete <session-id>
```

## Configuration
Session files are stored in `TRAKR_DIR` or `~/.trakr` by default.

## Todo
- [] Parse the cli arguments - (use `getopt_long`) and refactor [usage](#usage) to use subcommands.
- [] Create a parser for a session
- [] Work out saving the session data to a day file
