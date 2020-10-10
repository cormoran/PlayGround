package spring.batch.thoughput;

import org.springframework.batch.item.ItemProcessor;

public class IntegerIntegerItemProcessor implements ItemProcessor<Integer, Integer> {
    private int errorIndex;

    public IntegerIntegerItemProcessor(int errorIndex) {
        this.errorIndex = errorIndex;
    }

    @Override
    public Integer process(Integer item) throws Exception {
        if (item == errorIndex) {
            throw new Exception("error " + item);
        }
        return -1 * item;
    }
}
