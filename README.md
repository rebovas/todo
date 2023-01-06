### ToDo List  
  
Just personal project that allow to control list tasks on your day.  
  
#### Discription  

Have the archive that contain user's daily tasks. This utility allow manage tasks archive with various commands such as: 
add, delete, output, sort, and etc.  
Project consist of 2 main directories:  
        **bin/**    - binary files. Created during build project.  
        **modules/**    - source code

#### Development tasks  
- Write cmake script to build and install project.
Install project: copy got bin file in /usr/bin/ directory and make app 'todo' directory in /usr/share/ where contains archives with tasks.  
- Allow uesrs create and manage some archives (now only 1 archive on user).  
- Rewrite sort algorithm.  
- Optimize code. Where method 'Command::runExecution()', way to get now is the time and date (insert this in the method).  
