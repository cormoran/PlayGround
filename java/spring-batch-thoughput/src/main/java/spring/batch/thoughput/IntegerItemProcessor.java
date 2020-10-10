package spring.batch.thoughput;

import org.springframework.batch.item.ItemProcessor;

public class IntegerItemProcessor implements ItemProcessor<Integer, String> {
    private int errorIndex;

    public IntegerItemProcessor(int errorIndex) {
        this.errorIndex = errorIndex;
    }

    @Override
    public String process(Integer item) throws Exception {
        if (item == errorIndex) {
            throw new Exception("error " + item);
        }
        return String.valueOf(item);
    }
}
