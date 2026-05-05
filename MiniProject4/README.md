\# Simple Concurrent Web Server - CSAI 204



\## Project Description

A multi-threaded HTTP/1.0 web server implemented in C. It serves static HTML files and logs client requests.



\## Features Implemented

\- \*\*Socket Programming:\*\* Low-level OS primitives for networking.

\- \*\*Concurrency:\*\* Thread-per-request model using `pthread`.

\- \*\*Extensions:\*\*

&#x20; 1. \*\*Request Logging:\*\* All client GET requests are saved to `server.log`.

&#x20; 2. \*\*Secure File Paths:\*\* Prevents directory traversal attacks (`..`).



\## How to Build and Run

1\. Open WSL or Linux Terminal.

2\. Compile the server:

&#x20;  ```bash

&#x20;  gcc server.c -o server -lpthread

