RoofStat: Property Data Analyzer with C



This project is a console-based application written in C that allows users to interactively analyze property listings from a CSV file. It was developed as a case study for the \*\*Algorithm and Programming\*\* course at \*\*Bina Nusantara University\*\*.



📌 Overview



The application enables users to:

\- Read and display property listings

\- Search for specific data based on selected columns

\- Sort the data in ascending or descending order

\- Export filtered/sorted data to a new CSV file



The dataset contains columns such as:

\- `Location`

\- `City`

\- `Price`

\- `Rooms`

\- `Bathrooms`

\- `CarParks`

\- `Type`

\- `Furnish`



🚀 Features



1\. Display Data

\- Show a custom number of rows from the CSV.

\- If the number exceeds the actual rows, display all.



2\. Search Data

\- Search based on column name and query.

\- Displays all rows that match the query.



3\. Sort Data

\- Choose a column to sort by (e.g., `Price`, `Rooms`, etc.).

\- Select ascending (`asc`) or descending (`desc`) order.



4\. Export Data

\- Export the current dataset into a new `.csv` file.

\- The filename is specified by the user.



🛠️ Technologies



\- C Programming Language

\- Standard libraries: `stdio.h`, `stdlib.h`, `string.h`

\- Sorting with `qsort`

\- File parsing with `fgets` and `sscanf`



📂 How to Run



1\. Make sure you have a CSV file named `file.csv` in the same directory.

2\. Compile the program:

&nbsp;  ```bash

&nbsp;  gcc main.c -o property-analyzer



