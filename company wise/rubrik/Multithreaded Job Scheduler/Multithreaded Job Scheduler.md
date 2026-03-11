asks have dependencies (A → B → C).
You’re given helper APIs like getDependentTasks() to discover the DAG. Starting task is returned when input is blank. Each task has a doWork() function to execute. Rules:
* Parent tasks must finish before child tasks start.
* If any task throws an exception → stop everything immediately

Build a  Pipeline Manager where many job can be submitted and many jobs will have dependency on previous jobs one or more.

 A --> B --> C ------
  |                            |  
  |                             --> G
   ---> E --> F-------------^
 K--> L --> M

Now What we are given:
Job { // here A,B ,C are each a job
  jobId
  doWork() throws EnvironmentError
}

execute() -> need to implement this function in the class which I will create.

Now the pipeline can end under 2 conditions:
 1. Success -> when all jobs have executed.
 2. Failure --> If atleast one job fails, then it fails. No job is in a running state.