package dev.interviewer.invitations;
import org.springframework.stereotype.Service;
@Service public class InvitationService {
    private final InvitationMatcher matcher=new InvitationMatcher();
    public int maximum(int[][] compatibility){return matcher.maximumInvitations(compatibility);}
    public InvitationMatcher.MatchingResult assignments(int[][] compatibility){return matcher.maximumInvitationsWithAssignments(compatibility);}
}
