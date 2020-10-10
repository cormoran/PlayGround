package com.example.batchscheduler;

import org.springframework.batch.core.Job;
import org.springframework.batch.core.Step;
import org.springframework.batch.core.configuration.annotation.JobBuilderFactory;
import org.springframework.batch.core.configuration.annotation.StepBuilderFactory;
import org.springframework.batch.repeat.RepeatStatus;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;
import org.springframework.scheduling.concurrent.ThreadPoolTaskScheduler;

@Configuration
public class JobConfiguration {
    private JobBuilderFactory jobs;
    private StepBuilderFactory steps;

    public JobConfiguration(JobBuilderFactory jobs, StepBuilderFactory steps) {
        this.jobs = jobs;
        this.steps = steps;
    }

    @Bean
    public ThreadPoolTaskScheduler taskScheduler() {
        ThreadPoolTaskScheduler scheduler = new ThreadPoolTaskScheduler();
        scheduler.setPoolSize(10);
        return scheduler;
    }

    @Bean
    Job job() {
        return jobs.get("job").start(step()).build();
    }

    public Step step() {
        return steps.get("step").tasklet((contribution, chunkContext) -> {
            System.out.println("hello start");
            // simulate processing time
            Thread.sleep(10000);
            System.out.println("hello end");
            return RepeatStatus.FINISHED;
        }).build();
    }
}
