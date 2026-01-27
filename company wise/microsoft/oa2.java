import java.util.*;

// matrix[n][m] where n = number of days and m = number of hours per day . 

// matrix[i][j] =1 => there is a lecture on day i at hour j
//             =0 => no lecture
// if a student takes 1st lecture at hr x, and last ar hr y, then total time taken
// by him is y-x+1
// given a integer k : how many lecture he can skip

// ASK : return the minimum no of hrs he needs to stay in classroom
// by skipping k classes

// fyi : the input is a list of strings like {"10001","00111"} with a integer k 

public class oa2 {
    public static int getMinimumTime(List<String> schedule, int k) {
        int n = schedule.size();
        
        // For each day, calculate minimum time needed if we skip j lectures on that day
        // minTimeForDay[i][j] = minimum time on day i if we skip j lectures
        int[][] minTimeForDay = new int[n][];
        
        for (int day = 0; day < n; day++) {
            String daySchedule = schedule.get(day);
            List<Integer> lecturesOnDay = new ArrayList<>();
            
            for (int hour = 0; hour < daySchedule.length(); hour++) {
                if (daySchedule.charAt(hour) == '1') {
                    lecturesOnDay.add(hour);
                }
            }
            
            int totalLectures = lecturesOnDay.size();
            minTimeForDay[day] = new int[totalLectures + 1];
            
            // For each possible number of skips on this day
            for (int skips = 0; skips <= totalLectures; skips++) {
                if (skips >= totalLectures) {
                    // If we skip all lectures, time needed is 0
                    minTimeForDay[day][skips] = 0;
                } else {
                    int numToAttend = totalLectures - skips;
                    int minTime = Integer.MAX_VALUE;
                    
                    // Sliding window: find minimum span for attending numToAttend lectures
                    for (int i = 0; i + numToAttend - 1 < lecturesOnDay.size(); i++) {
                        int firstHour = lecturesOnDay.get(i);
                        int lastHour = lecturesOnDay.get(i + numToAttend - 1);
                        int timeNeeded = lastHour - firstHour + 1;
                        minTime = Math.min(minTime, timeNeeded);
                    }
                    minTimeForDay[day][skips] = minTime;
                }
            }
        }
        
        // DP: dp[day][skipsUsed] = minimum total time for first 'day' days using 'skipsUsed' skips
        int[][] dp = new int[n + 1][k + 1];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = Integer.MAX_VALUE;
            }
        }
        dp[0][0] = 0;
        
        // Fill DP table
        for (int day = 0; day < n; day++) {
            int maxSkipsOnDay = minTimeForDay[day].length - 1;
            
            for (int skipsUsed = 0; skipsUsed <= k; skipsUsed++) {
                if (dp[day][skipsUsed] == Integer.MAX_VALUE) continue;
                
                // Try skipping j lectures on this day
                for (int skipOnDay = 0; skipOnDay <= maxSkipsOnDay && skipsUsed + skipOnDay <= k; skipOnDay++) {
                    int newSkipsUsed = skipsUsed + skipOnDay;
                    int timeOnDay = minTimeForDay[day][skipOnDay];
                    dp[day + 1][newSkipsUsed] = Math.min(dp[day + 1][newSkipsUsed], dp[day][skipsUsed] + timeOnDay);
                }
            }
        }
        
        return dp[n][k];
    }
    
    // Test cases
    public static void main(String[] args) {
        // Test case 1: {"10001","00111"}, k=1
        List<String> schedule1 = Arrays.asList("10001", "00111");
        System.out.println("Test 1: " + getMinimumTime(schedule1, 1));  // Expected: 4
        
        // Test case 2: {"10001","00111"}, k=2
        List<String> schedule2 = Arrays.asList("0001", "0101","0110","0000");
        System.out.println("Test 2: " + getMinimumTime(schedule2, 3));  // Expected: 2
        
        // Test case 3: {"1111","1111"}, k=2
        List<String> schedule3 = Arrays.asList("010", "101","010");
        System.out.println("Test 3: " + getMinimumTime(schedule3, 1));  // Expected: 1
    }
}