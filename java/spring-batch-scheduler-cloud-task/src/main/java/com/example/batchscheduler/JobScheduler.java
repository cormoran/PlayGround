package com.example.batchscheduler;

import org.springframework.batch.core.Job;
import org.springframework.batch.core.JobParameters;
import org.springframework.batch.core.JobParametersBuilder;
import org.springframework.batch.core.launch.JobLauncher;
import org.springframework.batch.core.repository.JobExecutionAlreadyRunningException;
import org.springframework.batch.core.repository.JobInstanceAlreadyCompleteException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.autoconfigure.condition.ConditionalOnProperty;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
@ConditionalOnProperty(name = { "enableScheduling" }, havingValue = "true")
public class JobScheduler {
    private final Job job;
    private final JobLauncher JobLauncher;

    @Autowired
    public JobScheduler(Job job, JobLauncher jobLauncher) {
        this.job = job;
        this.JobLauncher = jobLauncher;
    }

    private void launch() throws Exception {
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

    @Scheduled(cron = "*/1 * * * * *")
    public void launchJob2() throws Exception {
        launch();
    }

    @Scheduled(cron = "*/1 * * * * *")
    public void launchJob3() throws Exception {
        launch();
    }

    @Scheduled(cron = "*/1 * * * * *")
    public void launchJob4() throws Exception {
        launch();
    }
}
