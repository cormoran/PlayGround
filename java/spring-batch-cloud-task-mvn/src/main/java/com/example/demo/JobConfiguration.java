package com.example.demo;

import org.springframework.batch.core.Job;
import org.springframework.batch.core.Step;
import org.springframework.batch.core.configuration.annotation.JobBuilderFactory;
import org.springframework.batch.core.configuration.annotation.StepBuilderFactory;
import org.springframework.batch.core.explore.JobExplorer;
import org.springframework.batch.core.launch.JobLauncher;
import org.springframework.batch.core.repository.JobRepository;
import org.springframework.batch.repeat.RepeatStatus;
import org.springframework.boot.autoconfigure.batch.JobLauncherApplicationRunner;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;
import org.springframework.scheduling.concurrent.ThreadPoolTaskScheduler;

@Configuration
@EnableConfigurationProperties({ JobConfigurationProperties.class })
public class JobConfiguration {
    private JobBuilderFactory jobs;
    private StepBuilderFactory steps;

    public JobConfiguration(JobBuilderFactory jobs, StepBuilderFactory steps) {
        this.jobs = jobs;
        this.steps = steps;
    }

    @Bean
    Job job() {
        return jobs.get("job-1").start(step()).next(step()).next(step()).build();
    }

    public Step step() {
        return steps.get("step").tasklet((contribution, chunkContext) -> {
            System.out.println("hello start");
            // simulate processing time
            Thread.sleep(30000);
            System.out.println("hello end");
            return RepeatStatus.FINISHED;
        }).build();
    }

    @Bean
    public ThreadPoolTaskScheduler taskScheduler() {
        ThreadPoolTaskScheduler scheduler = new ThreadPoolTaskScheduler();
        scheduler.setPoolSize(10);
        // scheduler.setDaemon(false);
        return scheduler;
    }

    @Bean
    public JobLauncherApplicationRunner jobLauncherApplicationRunner(JobLauncher jobLauncher, JobExplorer jobExplorer,
            JobRepository jobRepository, JobConfigurationProperties properties) {
        JobLauncherApplicationRunner runner = new JobLauncherApplicationRunner(jobLauncher, jobExplorer, jobRepository);
        runner.setJobNames(properties.jobName);
        System.out.println(properties.jobName);
        return runner;
    }
}
