*This project has been created as part of the 42 curriculum by adrianda*

## Description

`get_next_line` (GNL) is a C function that reads a single line from a file descriptor (FD), allowing you to read a text file one line at a time, regardless of the size of the buffer used for reading. 

While it sounds simple, this project serves as a deep dive into the concept of **static variables** in C and advanced memory management. The core challenge is maintaining the state (the unreturned, "leftover" characters read from the file) between multiple calls to the function without losing data or causing memory leaks. It pushes the boundaries of handling unpredictable edge cases, such as arbitrary buffer sizes, file reading errors, and EOF (End of File) handling without leaving dangling pointers.

### The Journey & Challenges

My biggest challenge in this project was mastering the flow of data: managing storage, line breaks, and return values. As the logic grew more complex, I constantly had to introduce new temporary variables just to preserve data states or hold memory references safely. 

To handle string manipulation, I adapted functions from my first project, [libft](https://github.com/devadrianoabner/lib_ft). Unlike my work on [ft_printf](https://github.com/devadrianoabner/ft_printf) where the entire library could be linked, the GNL subject strictly forbids using the compiled `libft` archive. Instead, I had to extract and modify specific utility functions to meet GNL's strict memory and bug-prevention requirements.

The second major hurdle was defensive programming—figuring out exactly where and how to implement memory checks to prevent memory leaks and segmentation faults during execution.

GNL was my third project at École 42. While I feel I still have a lot to learn to truly master memory management in C, this project represents a massive leap in my technical development and debugging skills compared to my earlier work.

## Instructions

### Build

Since this project is not a standalone program but a utility function, it is meant to be compiled alongside your project's main files. The buffer size can be defined at compile time using the `-D BUFFER_SIZE=n` flag.

Compile your code with `get_next_line.c` and `get_next_line_utils.c`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl

```
(If no BUFFER_SIZE is provided during compilation, the header defaults to 42).

### Use in another project

1. Include the header in your C files and call the function within a loop to read a file line by line:

	```c
	#include <fcntl.h>
	#include <stdio.h>
	#include "get_next_line.h"
	
	
	int main(void)
	{
		int	fd = open("example.txt", O_RDONLY);
		char	*line;
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
		return (0);
	}
	```

## Algorithm & Justification

The algorithm is designed around a Read, Append, Extract, and Save cycle, utilizing a single static pointer (remainder) to track leftover text between function calls.

Read & Append (ft_read_buff): The function allocates a temporary read buffer on the Heap. It reads up to BUFFER_SIZE characters from the file descriptor. The read chunk is concatenated to the static remainder string using ft_strjoin. This loop continues until a newline character (\n) is detected in the remainder or the end of the file is reached (read returns 0).

Extract (ft_substr): Once the loop stops, the algorithm calculates the length of the string up to the \n (inclusive) and extracts it into a new string (line) to be returned to the user.

Save: The remaining characters (everything after the newline) are extracted into a new allocated string, which overwrites the static remainder. The old remainder is freed.

Justification: This approach is highly robust because it decouples the physical read size (BUFFER_SIZE) from the logical line length. By accumulating text first and searching for the newline later, it perfectly handles lines that are much larger than the buffer, or situations where multiple newlines are captured in a single read. Using Heap allocation for the temporary buffer ensures the algorithm scales safely, avoiding Stack Overflow issues when tested with massive sizes (e.g., BUFFER_SIZE=10000000).

## Technical Choices

On top of the mandatory 42 Norm (strict 25 lines per function), this project follows specific architectural rules:

Single Static Variable — Only one static variable is used to keep track of the remaining text, minimizing persistent memory footprints.

Heap-based Buffer — The temporary buffer used for the read() system call is dynamically allocated via malloc instead of a static array. This prevents segmentation faults caused by stack exhaustion when compiling with an excessively large BUFFER_SIZE.

Defensive Memory Management — Edge cases are heavily protected:

If read() fails (returns < 0), the accumulated static variable is instantly freed to prevent data corruption and leaks.

At EOF, if the static variable holds an empty string (""), it is explicitly freed and set to NULL, passing rigorous memory leak tests.

No Libft — As per project rules, external libraries are forbidden. String manipulation functions were rewritten from scratch in get_next_line_utils.c.

## Library Overview

### The functions in GNL

| Function | Description |
| --- | --- |
| `get_next_line`	| The main entry point; handles flow control and returns the next line. |
| `ft_read_buff`	| Static helper; reads from FD and populates the static buffer |
| `ft_strlen` 		| Returns the length of a string |
| `ft_strchr`		| Finds the first occurrence of a character in a string |
| `ft_calloc`		| Allocates and zero-initialises memory |
| `ft_substr`		| Allocates a substring extracted from a string |
| `ft_strjoin`		| Allocates a new string that concatenates two strings |

## Resources

### References

Linux man pages, section 2 — man read behavior, specifically understanding its return values (bytes read, 0 for EOF, and -1 for errors).

GNU C Library: Static Variables — Understanding the lifespan and initialization of static variables in C.

### AI usage

- **Debugging Stack Overflows** — Initially, the read buffer was declared as an array (char buf[BUFFER_SIZE + 1];). When running a community tester with BUFFER_SIZE = 10000000, the program crashed violently (SIGSEGV). The AI clarified the difference between Stack (hardware-limited, fast memory) and Heap (dynamic, larger memory) allocations, prompting the refactor to use malloc for the buffer.

- **Tracing Memory Leaks at EOF** — Discussed edge cases where Valgrind reported lost bytes at the end of file execution. The AI helped trace how ft_substr allocated a tiny \0 string when the file ended without a trailing newline. This led to the implementation of strict cleanup conditionals (if (remainder == NULL || remainder[0] == '\0')) to free empty remnants before returning NULL.
