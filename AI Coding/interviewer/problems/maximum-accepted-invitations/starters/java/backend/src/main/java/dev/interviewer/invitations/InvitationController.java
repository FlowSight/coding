package dev.interviewer.invitations;
import java.util.Map; import org.springframework.web.bind.annotation.*;
@RestController @RequestMapping("/api/invitations") @CrossOrigin(origins="http://localhost:5173")
public class InvitationController {
    private final InvitationService service; public InvitationController(InvitationService service){this.service=service;}
    @PostMapping("/maximum") public Map<String,Integer> maximum(@RequestBody MatrixRequest request){return Map.of("count",service.maximum(request.compatibility()));}
    @PostMapping("/assignments") public InvitationMatcher.MatchingResult assignments(@RequestBody MatrixRequest request){return service.assignments(request.compatibility());}
    public record MatrixRequest(int[][] compatibility){}
}
