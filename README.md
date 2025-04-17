# TODO LIST
## Features

- **Task Organization**: Each task includes name, category, completion status, deadline, priority, and status

- **Subtasks**: you can add some subtasks to your main tasks

- **Priority Levels**: Assign __High__, __Medium__, or __Low__ priority to tasks

- **Status Tracking**: Mark tasks as __Done__, __In Progress__, or __Not Started__

- **Deadline Notifications**: Visual indicators for tasks __due within 24 hours__

- **Filtering**: Filter tasks by __category__, __priority__, or __status__

- **Automatic Sorting**: Tasks are automatically sorted by __priority__ and __deadline__

- **Persistent Storage**: All tasks are __saved to file__ and __loaded on startup__

## Usage

To compile and run the program:

```
g++ -o todolist main.cpp
./todolist
```

### Commands

| Command | Description |
|---------|-------------|
| `add` | Add a new task with all details |
| `mod [index]` | Modify the task at the specified index |
| `rm [index]` | Remove the task at the specified index |
| `show [index]` | Display detailed information about the task at the specified index |
| `filter` | Filter tasks by category, priority, or status |
| `exit` | Save all tasks and exit the program |

### Examples

- To add a new task: `add` ([explanation](#further-explanation))
- To modify the first task: `mod 0`([explanation](#further-explanation))
- To delete the second task: `rm 1`
- To view details of the third task: `show 2`
- To filter tasks: `filter` ([explanation](#further-explanation))
- To save and exit: `exit`

### Further explanation
Once you use the`add` ,  `mod` and `filter` commands, you can follow the instructions that appear on the terminal.

## Task Properties<small> (MoreTask) </small>

- **Name<small> (string) </small>**: Task title
- **Category<small> (string) </small>**: Task category
- **Completion<small> (bool) </small>**: Yes/No
- **Deadline<small> (Date) </small>**: Date and time in format YYYY MM DD HH
- **Priority<small> (int) </small>**: High (1), Medium (2), Low (3)
- **Status<small> (int) </small>**: Done (1), In Progress (2), Not Started (3)
- **Subtasks<small> (Basic_task) </small>**: Optional list of simpler tasks