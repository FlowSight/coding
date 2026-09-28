package dev.interviewer.router;
import org.springframework.http.ResponseEntity;import org.springframework.web.bind.annotation.*;
@RestController @RequestMapping("/api/routes") @CrossOrigin(origins="http://localhost:5173")
public class RouterController{
 private final RouterService service;public RouterController(RouterService service){this.service=service;}
 @PostMapping("/match")public ResponseEntity<UrlRouter.RouteMatch>match(@RequestBody MatchRequest request){return service.match(request.path()).map(ResponseEntity::ok).orElseGet(()->ResponseEntity.notFound().build());}
 @PostMapping public void add(@RequestBody AddRouteRequest request){service.add(request.pattern(),request.handler());}
 @DeleteMapping public boolean remove(@RequestBody MatchRequest request){return service.remove(request.path());}
 public record MatchRequest(String path){}public record AddRouteRequest(String pattern,String handler){}
}
