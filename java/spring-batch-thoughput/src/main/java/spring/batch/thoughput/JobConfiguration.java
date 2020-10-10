package spring.batch.thoughput;

import java.util.ArrayList;
import java.util.List;

import org.springframework.batch.core.Job;
import org.springframework.batch.core.Step;
import org.springframework.batch.core.configuration.annotation.JobBuilderFactory;
import org.springframework.batch.core.configuration.annotation.StepBuilderFactory;
import org.springframework.batch.core.launch.support.RunIdIncrementer;
import org.springframework.batch.item.ItemReader;
import org.springframework.batch.item.ItemWriter;
import org.springframework.batch.item.support.ListItemReader;
import org.springframework.batch.item.support.ListItemWriter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class JobConfiguration {
    @Autowired
    private JobBuilderFactory jobs;
    @Autowired
    private StepBuilderFactory steps;

    @Bean
    Job job() {
        // return jobs.get("job1").start(step1()).incrementer(new
        // RunIdIncrementer()).build();
        return jobs.get("job1").start(step1()).next(step2()).build();
    }

    public Step step1() {
        return steps.get("step1").<Integer, String>chunk(100).reader(reader()).processor(new IntegerItemProcessor(-1))
                .writer(writer()).build();
    }

    public Step step2() {
        return steps.get("step2").<Integer, String>chunk(100).reader(reader()).processor(new IntegerItemProcessor(1000))
                .writer(writer()).build();
    }

    public ItemReader<Integer> reader() {
        ArrayList<Integer> arr = new ArrayList();
        for (int i = 0; i < 100000; i++) {
            arr.add(i);
        }
        return new ListItemReader<>(arr);
    }

    public ItemWriter<String> writer() {
        return new ListItemWriter<String>() {
            @Override
            public void write(List<? extends String> items) throws Exception {
                super.write(items);
            }
        };
    }
}
