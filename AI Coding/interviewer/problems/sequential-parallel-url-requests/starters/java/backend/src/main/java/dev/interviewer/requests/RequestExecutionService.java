package dev.interviewer.requests;
import java.util.List;import org.springframework.stereotype.Service;
@Service public class RequestExecutionService{
 private final UrlRequestExecutor executor=new UrlRequestExecutor();
 private final UrlRequestExecutor.UrlFetcher demoFetcher=url->new UrlRequestExecutor.Response(url,200,"preview:"+url);
 public List<UrlRequestExecutor.Response> sequential(List<String>urls){return executor.fetchSequential(urls,demoFetcher);}
 public List<UrlRequestExecutor.Response> parallel(List<String>urls){return executor.fetchParallel(urls,demoFetcher);}
}
