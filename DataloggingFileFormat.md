# Introduction #

Datalogging is performed on a FAT32 filesystem stored on an SD memory card.

This wiki page gives a specification for how data is logged onto the SD card.

# Filesystem Layout #

Every time datalogging is initiated, a new session is created. Sessions are numbered sequentially. Up to 1,000 sessions, from 000 to 999, may be used. After this number is exceeded, the card must have the data removed to continue. The lowest free number is used.

All data is stored under the "dlog" root with "Snnn" being the folder name (where nnn is the identifier from 000 to 999.)

Each session folder contains the configuration file for that session (cfg.ini), and a data file, data.bin. The data file is preceded by a header, and then each 'row' of data, sequentially stored. The configuration file and the data file are explained below.

As the microcontroller is managing an entire filesystem, keeping the filesystem clean is important. Otherwise, the microcontroller may not be able to log data at the maximum rate, and gaps in the data may occur. In all cases, the micro will write at its maximum possible speed.

# Configuration File #
[TODO](TODO.md)

# Data file #

## Header ##

The data rows are preceded by a 32 byte header.

| **field name** | **data type** | **size (bytes)** | **description** |
|:---------------|:--------------|:-----------------|:----------------|
| identifier     | uint32        | 4                | magic identifier: 0x05D00000 |
| compression    | byte          | 1                | compression mode: 0x00 (uncompressed) |
| row size       | uint16        | 2                | row size, 4 to 512 bytes (includes checksum) |
| time           | time          | 4                | time of datalogging start |
| reserved       | byte          | 21               | always 0x00, unused |

## Rows ##

Each row is stored sequentially in the file. To ensure integrity, an Adler-32 checksum of each row is added to the end of the row. If a row is corrupt, then it must be discarded. Each row contains one item of each field described in the configuration file.