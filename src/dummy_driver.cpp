#include <string>
#include "mpi.h"

// Forward declaration
static cmdOptions *processCmdLineOptions(int argc, char **argv);

int main(int argc, char* argv[]) {

  auto ierr = MPI_Init(&argc, &argv);
  if (ierr != MPI_SUCCESS) {
    MPI_Abort(MPI_COMM_WORLD, ierr);
  }

  MPI_Comm comm;
  int rank, size;
  MPI_Comm_dup(MPI_COMM_WORLD, &comm);
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  auto cmd_opts = processCmdLineOptions(argc, argv);
  std::string cache_dir;
  nekrs::setup(comm, cmd_opts->buildOnly, cmd_opts->sizeTarget, cmd_opts->ciMode, cache_dir, 
      cmd_opts->setupFile);
  if (cmd_opts->buildOnly) {
    MPI_Finalize();
    return EXIT_SUCCESS;
  }

  int tstep = 1;
  auto time = nekrs::startTime();
  while (time < nekrs::finalTime()) {

    auto is_output_step = (nekrs::outputStep() > 0) && 
        (tstep % nekrs::outputStep() == 0 || tstep == nekrs::NtimeSteps());

    nekrs::runstep(time, tstep);

    time += nekrs::dt();

    if (is_output_step) {
      nekrs::copyToNek(time, tstep);
    }

    nekrs::udfExecuteStep(time, tstep, (int) is_output_step);

    if (is_output_step) {
      nekrs::nekOutfld();
    }

    ++tstep;
  }

  MPI_Finalize();
  return EXIT_SUCCESS;
}

// From src/main.cpp
static cmdOptions *processCmdLineOptions(int argc, char **argv) 
{
  int rank;
  MPI_Comm_rank(comm, &rank);
 
  cmdOptions *cmdOpt = new cmdOptions();
 
  int err = 0;
  int foundSetup = 0;

  if (rank == 0){
    while(1){
      static struct option long_options[] =
      {
          {"setup", required_argument, 0, 's'},
          {"cimode", required_argument, 0, 'c'},
          {"build-only", required_argument, 0, 'b'},
          {0, 0, 0, 0}
      };
      int option_index = 0;
      int c = getopt_long (argc, argv, "s:d:", long_options, &option_index);
    
      if (c == -1)
        break;
    
      switch(c){ 
          case 's':
              cmdOpt->setupFile.assign(optarg);  
              cmdOpt->setupFile = cmdOpt->setupFile + ".par";
              if (const char *ptr = realpath(cmdOpt->setupFile.c_str(), NULL)) 
                foundSetup = 1;
              else 
                std::cout << "ERROR: Cannot find " << cmdOpt->setupFile << "!\n";
              break;  
          case 'b':  
              cmdOpt->buildOnly = 1;
              cmdOpt->sizeTarget = atoi(optarg);  
              break; 
           case 'c':  
              cmdOpt->ciMode = atoi(optarg);
              if (cmdOpt->ciMode < 1) {
                std::cout << "ERROR: ci test id has to be >0!\n";
                err = 1;
              }
              break;  
          default:  
              err = 1;
      }
    }  
    if (!foundSetup) err = 1;
  } 

  MPI_Bcast(&err, sizeof(err), MPI_BYTE, 0, comm);
  if (err) {
    if (rank == 0)
      std::cout << "usage: ./nekrs --setup <case name> [ --build-only <#procs> ] [ --cimode <id> ]"
           << "\n";
    MPI_Finalize(); 
    exit(1);
  }

  char buf[FILENAME_MAX];
  strcpy(buf, cmdOpt->setupFile.c_str());
  MPI_Bcast(buf, sizeof(buf), MPI_BYTE, 0, comm);
  cmdOpt->setupFile.assign(buf);
  MPI_Bcast(&cmdOpt->buildOnly, sizeof(cmdOpt->buildOnly), MPI_BYTE, 0, comm);
  MPI_Bcast(&cmdOpt->sizeTarget, sizeof(cmdOpt->sizeTarget), MPI_BYTE, 0, comm);
  MPI_Bcast(&cmdOpt->ciMode, sizeof(cmdOpt->ciMode), MPI_BYTE, 0, comm);

 return cmdOpt;
}