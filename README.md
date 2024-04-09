# ASCII Compression Tool

## Overview

This repository hosts an ASCII Compression Tool. The tool significantly reduces the size of text files without compromising their integrity. For larger files, exceeding 4096 bytes, the tool employs a multi-threaded approach, utilizing 3 threads to enhance processing speed and efficiency. This ensures that even substantial text files are compressed swiftly.

## Features

- **Compression**: Reduces text file size effectively, ensuring minimal loss of data integrity.
- **Multi-Threading on Large Files**: Utilizes 3 threads for files larger than 4096 bytes.

## Usage

The correct invocation syntax is as follows:

    ./wzip [text file 1], [text file 2], ...

A minimum of 1 argument is required.

### Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/yourusername/ascii-compression-tool.git
