#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#define JOBS_QUANTITY 10

using cousint = const unsigned int;
using namespace std;

struct Job {
    unsigned proccess_time;
    unsigned finish_time;

    Job(cousint prc_time, cousint fnsh_time) : proccess_time(prc_time), finish_time(fnsh_time) {}
    Job() : proccess_time(0), finish_time(0) {}

    static Job makeJob(cousint prc_time, cousint fnsh_time) {
        Job job(prc_time, fnsh_time);
        return job;
    }

    static vector<Job> randomJobs() {
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> uni(0, 100);
        vector<Job> random_jobs;
        for(int i = 0; i < JOBS_QUANTITY; i++) {
            random_jobs.push_back(Job::makeJob(uni(rng), uni(rng)));
        }

        return random_jobs;
    }
};


bool jobSorter(const Job& some_job, const Job& other_job) {
    return some_job.finish_time > other_job.finish_time;
}

int main() {
    vector<Job> random_jobs = Job::randomJobs();
    cout << "jobs: " <<endl;
    for(size_t i = 0; i < random_jobs.size(); ++i) {
        cout << "proccess_time: "<< random_jobs[i].proccess_time << " // finish_time: " << random_jobs[i].finish_time <<endl;
    }
    cout <<endl;

    sort(random_jobs.begin(), random_jobs.end(), &jobSorter);

    unsigned int final_time = 0;
    unsigned int super_computer_time = 0;
    for(size_t i = 0; i < JOBS_QUANTITY; ++i) {
        super_computer_time += random_jobs[i].proccess_time;
        if (random_jobs[i].proccess_time + random_jobs[i].finish_time > final_time) {
            final_time = random_jobs[i].proccess_time + random_jobs[i].finish_time;
        } else {/*donot*/}
    }

    cout << "jobs order:" <<endl;
    for(size_t i = 0; i < random_jobs.size(); ++i) {
        cout << "proccess_time: "<< random_jobs[i].proccess_time << " // finish_time: " << random_jobs[i].finish_time <<endl;
    }
    cout << "final time = " << final_time <<endl;

    return 0;
}
