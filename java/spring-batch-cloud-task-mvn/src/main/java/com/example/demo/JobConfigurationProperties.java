package com.example.demo;

import org.springframework.boot.context.properties.ConfigurationProperties;

import lombok.Data;

@ConfigurationProperties(prefix = "app")
@Data
public class JobConfigurationProperties {
    /**
     * Hello world
     */
    boolean enableScheduling = false;
    /**
     * Hello good
     */
    String jobName = "none";
}
