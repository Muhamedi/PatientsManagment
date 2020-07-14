1. Enter the root directory using the command: cd covlist

2. Enter the following commands to compile or generate documentation:
   a) make all
   b) make dox

3. Enter the output/exe directory to start the application using the following command:
   cd output/exe

4. Enter the output/docu/html directory to view documentation using the following command:
   cd output/docu/html 
   and then open the index.html file.

5. Enter the following command to append a patient into the file: 
   ./covlist -f "emriFajllit" -a

6. Enter the following command to list all the patients saved into the file: 
   ./covlist -f "emriFajllit" -l

7. You can go to the root of the exercise directory and type make clean
   to clean and remove the output directory with its contents
