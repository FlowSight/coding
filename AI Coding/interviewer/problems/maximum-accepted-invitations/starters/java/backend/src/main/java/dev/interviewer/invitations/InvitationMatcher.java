package dev.interviewer.invitations;
import java.util.*;
public final class InvitationMatcher {
    public int maximumInvitations(int[][] compatibility) {
        validateGrid(compatibility); if (compatibility.length==0)return 0;
        int[] girlToBoy=new int[compatibility[0].length]; Arrays.fill(girlToBoy,-1); int accepted=0;
        for(int boy=0;boy<compatibility.length;boy++) if(tryMatch(boy,compatibility,girlToBoy,new boolean[girlToBoy.length])) accepted++;
        return accepted;
    }
    private boolean tryMatch(int boy,int[][] compatibility,int[] girlToBoy,boolean[] visitedGirls){
        for(int girl=0;girl<compatibility[boy].length;girl++){if(compatibility[boy][girl]==0||visitedGirls[girl])continue;visitedGirls[girl]=true;
            // Seeded bug: occupied matches are skipped instead of rerouted.
            if(girlToBoy[girl]==-1){girlToBoy[girl]=boy;return true;}}
        return false;
    }
    public MatchingResult maximumInvitationsWithAssignments(int[][] compatibility){throw new UnsupportedOperationException("Implement Return Match Assignments");}
    public record Pair(int boy,int girl){}
    public record MatchingResult(int count,List<Pair> assignments){public MatchingResult{assignments=List.copyOf(assignments);}}
    public static final class IncrementalInvitationMatcher{
        private final int boyCount,girlCount; private final List<Pair> compatibility=new ArrayList<>();
        public IncrementalInvitationMatcher(int boyCount,int girlCount){if(boyCount<0||girlCount<0)throw new IllegalArgumentException("Counts must be non-negative");this.boyCount=boyCount;this.girlCount=girlCount;}
        public void addCompatibility(int boy,int girl){throw new UnsupportedOperationException("Implement Incremental Compatibility Updates");}
        public MatchingResult currentMatching(){throw new UnsupportedOperationException("Implement Incremental Compatibility Updates");}
        public int boyCount(){return boyCount;} public int girlCount(){return girlCount;}
    }
    private static void validateGrid(int[][] grid){if(grid==null)throw new IllegalArgumentException("Grid must not be null");int width=grid.length==0?0:requireRow(grid[0]).length;for(int[] row:grid)if(requireRow(row).length!=width)throw new IllegalArgumentException("Grid must be rectangular");}
    private static int[] requireRow(int[] row){if(row==null)throw new IllegalArgumentException("Rows must not be null");return row;}
}
