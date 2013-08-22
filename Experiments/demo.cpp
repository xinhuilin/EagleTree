#include "../ssd.h"
#include <unistd.h>   // chdir
#include <sys/stat.h> // mkdir

using namespace ssd;

int main()
{
	printf("Running EagleTree\n");
	set_small_SSD_config();

	string name  = "/exp_interleaving/";
	string exp_folder = get_current_dir_name() + name;
	printf("creating exp folder:  %s\n", get_current_dir_name());
	Experiment::create_base_folder(exp_folder.c_str());

	Workload_Definition* init = new Init_Workload();
	string calibration_file = "calib.txt";
	Experiment::calibrate_and_save(init, calibration_file);

	double writes_probability = 0.5;
	Workload_Definition* workload = new Asynch_Random_Workload(writes_probability);
	Experiment* e = new Experiment();
	e->set_calibration_file(calibration_file);
	e->set_workload(workload);
	e->set_io_limit(50000);

	e->set_generate_trace_file(true);
	e->draw_graphs();

	delete workload;
	delete init;
	return 0;
}
