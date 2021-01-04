package com.example.batchscheduler;

import java.util.Set;

import org.springframework.batch.core.Job;
import org.springframework.batch.core.JobParameters;
import org.springframework.batch.core.JobParametersBuilder;
import org.springframework.batch.core.launch.JobLauncher;
import org.springframework.batch.core.launch.JobOperator;
import org.springframework.batch.core.repository.JobExecutionAlreadyRunningException;
import org.springframework.batch.core.repository.JobInstanceAlreadyCompleteException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.SmartLifecycle;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
public class JobScheduler implements SmartLifecycle {
    private final Job job;
    private final JobLauncher JobLauncher;
    private boolean running = false;
    private JobOperator jobOperator;

    @Autowired
    public JobScheduler(Job job, JobLauncher jobLauncher, JobOperator jobOperator) {
        this.job = job;
        this.JobLauncher = jobLauncher;
        this.jobOperator = jobOperator;
    }

    private void launch() throws Exception {
        if (!running) {
            System.out.println("Skip since it's not running");
            return;
        }
        long t = System.currentTimeMillis();
        System.out.println("Go Go!!");
        final JobParameters jobParameters = new JobParametersBuilder().addLong("param1", t).toJobParameters();
        try {
            JobLauncher.run(job, jobParameters);
        } catch (JobExecutionAlreadyRunningException e) {
            System.out.println("Job already running! " + t);
        } catch (JobInstanceAlreadyCompleteException e) {
            System.out.println("Job already completed! " + t);
        }
    }

    @Scheduled(cron = "*/1 * * * * *")
    public void launchJob() throws Exception {
        launch();
    }

    @Override
    public void start() {
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        System.out.println("start job scheduler job");
        this.running = true;
    }

    @Override
    public void stop() {
        running = false;
        System.out.println("start stopping job");
        Set<Long> executionIds;
        try {
            executionIds = jobOperator.getRunningExecutions("job1");
            for (Long executionId : executionIds) {

                System.out.println("stop execution " + executionId);
                try {
                    jobOperator.stop(executionId);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
            boolean finished = false;
            for (int i = 0; i < 10; i++) {
                Thread.sleep(1000);
                if (jobOperator.getRunningExecutions("job1").size() == 0) {
                    finished = true;
                    break;
                }
            }
            if (!finished) {
                System.out.println("some job was not stopped within timeout");
            } else {
                System.out.println("finished");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public boolean isRunning() {
        return running;
    }
}
