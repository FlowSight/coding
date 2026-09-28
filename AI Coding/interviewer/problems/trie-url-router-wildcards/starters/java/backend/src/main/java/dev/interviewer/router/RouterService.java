package dev.interviewer.router;
import java.util.Optional;import org.springframework.stereotype.Service;
@Service public class RouterService{
 private final UrlRouter router=new UrlRouter();
 public RouterService(){router.add("/users/new/settings","settings");router.add("/users/:id/profile","profile");}
 public void add(String pattern,String handler){router.add(pattern,handler);}
 public Optional<UrlRouter.RouteMatch>match(String path){return router.match(path);}
 public boolean remove(String pattern){return router.remove(pattern);}
}
