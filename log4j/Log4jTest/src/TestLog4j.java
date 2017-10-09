/**
 * Created by wengwei on 17-5-30.
 */
import org.apache.log4j.*;
//学习网站：http://www.yiibai.com/log4j/
public class TestLog4j {
    public static void main(String[] args){
        PropertyConfigurator.configure("log4j.properties");
        Logger logger = Logger.getLogger(TestLog4j.class);
        logger.debug("debug");
        logger.error("error");
    }
}
