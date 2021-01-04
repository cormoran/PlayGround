package com.example.batchscheduler;

import java.util.Set;

import org.springframework.batch.core.Job;
import org.springframework.batch.core.JobExecution;
import org.springframework.batch.core.Step;
import org.springframework.batch.core.configuration.annotation.JobBuilderFactory;
import org.springframework.batch.core.configuration.annotation.StepBuilderFactory;
import org.springframework.batch.core.launch.JobOperator;
import org.springframework.batch.repeat.RepeatStatus;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;
import org.springframework.scheduling.concurrent.ThreadPoolTaskScheduler;

@Configuration
public class JobConfiguration implements AutoCloseable {
    private JobBuilderFactory jobs;
    private StepBuilderFactory steps;
    private JobOperator jobOperator;

    public JobConfiguration(JobBuilderFactory jobs, StepBuilderFactory steps, JobOperator jobOperator) {
        this.jobs = jobs;
        this.steps = steps;
        this.jobOperator = jobOperator;
    }

    @Bean
    public ThreadPoolTaskScheduler taskScheduler() {
        ThreadPoolTaskScheduler scheduler = new ThreadPoolTaskScheduler();
        scheduler.setPoolSize(10);
        return scheduler;
    }

    @Bean
    Job job() {
        return jobs.get("job1").start(step()).build();
    }

    public Step step() {
        return steps.get("step").tasklet((contribution, chunkContext) -> {
            System.out.println("hello start");
            // simulate processing time
            try {
                Thread.sleep(30000);
            } catch (Exception e) {

            }
            System.out.println("hello end");
            return RepeatStatus.FINISHED;
        }).build();
    }

    @Override
    public void close() throws Exception {
        // Set<Long> executionIds = jobOperator.getRunningExecutions("job");
        // for (Long executionId : executionIds) {
        // jobOperator.stop(executionId);
        // }
        // boolean finished = false;
        // for (int i = 0; i < 10; i++) {
        // Thread.sleep(1000);
        // if (jobOperator.getRunningExecutions("job").size() == 0) {
        // finished = true;
        // break;
        // }
        // }
        // if (!finished) {
        // System.out.println("some job was not stopped within timeout");
        // } else {
        // System.out.println("finished");
        // }
    }
}
