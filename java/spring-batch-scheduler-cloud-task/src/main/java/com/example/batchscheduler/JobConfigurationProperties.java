package com.example.batchscheduler;

import org.springframework.boot.context.properties.ConfigurationProperties;

import lombok.Data;

@ConfigurationProperties(prefix = "app")
@Data
public class JobConfigurationProperties {
    boolean enableScheduling = false;
    String jobName = "none";
}
