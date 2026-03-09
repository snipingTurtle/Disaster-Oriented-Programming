# Disaster-Oriented Programming: Hall Management System

A C++ based Hall Management System designed for efficient handling of student complaints and official notice board announcements.

## Features
- **Complaint System**: Students can file grievances, which are then persisted in `complaints.txt`.
- **Notice Board**: Authorized personnel can post announcements for students to read.
- **Persistent Data**: All records are stored in CSV-style text files for easy retrieval and management.
- **Database Handler**: Centralized logic for reading/writing data to the filesystem.

## Project Structure
- `include/`: Header files (`.hpp`)
- `src/`: Implementation files (`.cpp`)
- `data/`: Persistence files (e.g., `complaints.txt`, `notices.txt`)

## Compilation
Use the provided `CMakeLists.txt` to build the project:
```bash
mkdir build && cd build
cmake ..
make
./HMS
```

## Authors
- snipingTurtle Team
- Disaster-Oriented Programming Group
