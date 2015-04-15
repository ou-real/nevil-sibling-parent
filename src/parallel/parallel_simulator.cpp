#include "nevil/parallel/parallel_simulator.hpp"

void nevil::parallel::simulator(nevil::args &cl_args)
{
  using namespace nevil;
  using namespace nevil::parallel;

  srand(time(0));
  
  // Default values
  int num_threads = os::get_num_processors() - 1;
  int num_trials = 30;
  bool seeded_trial = false;

  args::const_iterator it;
  // If the number of threads is provided
  if ((it = cl_args.find("tn")) != cl_args.end())
  {
    num_threads = std::stoi(it->second);
    if (num_threads == 0)
      num_threads = os::get_num_processors();
    else if (num_threads < 0)
      num_threads = std::max(1, os::get_num_processors() + num_threads);
  }

  // If the number of trials is provided
  if ((it = cl_args.find("mt")) != cl_args.end())
    num_trials = std::stoi(it->second);

  // Don't spawn more threads than number of trials
  num_threads = std::min(num_threads, num_trials);

  // If the seed is provided, only run one trial with that seed
  if ((it = cl_args.find("rs")) != cl_args.end())
    seeded_trial = true;

  // Don't spawn threads if the number of threads is 1
  // Or Seed is provided
  if (num_threads == 1 || seeded_trial)
  {
    unsigned seed = rand();
    if (seeded_trial)
      seed = std::stoll(cl_args["rs"]);

    trial_controller controller (1, seed, cl_args);
    controller.run();
    return;
  }

  // Using pthread to run trials in parallel
  std::vector<pthread_t> threads(num_threads);
  std::vector<thread_data> data(num_threads);
  int load = num_trials / num_threads;
  int remeinder = num_trials % num_threads;

  // Launching threads
  for(int i = 0; i < num_threads; ++i)
  {
    data[i].cl_args = &cl_args;
    data[i].random_seed = rand();
    // Crazy load balancing... move along
    data[i].start_id = (i == 0) ? 1 : data[i-1].end_id;
    data[i].end_id = data[i].start_id + load + (remeinder-- > 0);

    int rc = pthread_create(&threads[i], NULL, parallel::_run_trial, (void *)&data[i]);
    if (rc)
    {
      std::cerr << "Error: unable to create thread.\nAborting now..." << std::endl;
      exit(-1);
    }
  }
  // pthread_exit(NULL);
  for (auto t : threads)
    pthread_join(t, NULL);
}

void *nevil::parallel::_run_trial(void *data)
{
  using namespace nevil;

  parallel::thread_data *t_data = (thread_data *) data;
  srand(t_data->random_seed);

  for (size_t i = t_data->start_id; i < t_data->end_id; ++i)
  {
    trial_controller controller (i, rand(), *(t_data->cl_args));
    controller.run();
  }
  pthread_exit(NULL);
}

