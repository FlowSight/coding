import java.io.*;
import java.net.*;
import java.util.*;

public class LongestEvent {

    public String longestDuration(String organizer, String genre) throws Exception {
        String baseUrl = "https://jsonmock.hackerrank.com/api/events?organized_by="
                         + URLEncoder.encode(organizer, "UTF-8");

        String bestId = null;
        int maxDuration = -1;
        int totalPages = 1;

        for (int page = 1; page <= totalPages; page++) {
            String json = fetchUrl(baseUrl + "&page=" + page);

            if (page == 1) {
                totalPages = getIntValue(json, "total_pages");
            }

            List<String> events = splitObjects(json, "data");
            for (String event : events) {
                if (!event.contains("\"" + genre + "\"")) continue;

                int duration = getIntValue(event, "duration");
                String id = getStringValue(event, "id");

                if (duration > maxDuration ||
                    (duration == maxDuration && id.compareTo(bestId) < 0)) {
                    maxDuration = duration;
                    bestId = id;
                }
            }
        }

        return bestId == null ? "-1" : bestId;
    }

    // Extract int value for a key like "duration": 5
    private int getIntValue(String json, String key) {
        String search = "\"" + key + "\":";
        int idx = json.indexOf(search);
        if (idx == -1) return 0;
        idx += search.length();
        // skip whitespace
        while (idx < json.length() && json.charAt(idx) == ' ') idx++;
        int end = idx;
        while (end < json.length() && Character.isDigit(json.charAt(end))) end++;
        return Integer.parseInt(json.substring(idx, end));
    }

    // Extract string value for a key like "id": "abc-123"
    private String getStringValue(String json, String key) {
        String search = "\"" + key + "\":\"";
        int idx = json.indexOf(search);
        if (idx == -1) return "";
        idx += search.length();
        int end = json.indexOf("\"", idx);
        return json.substring(idx, end);
    }

    // Split the "data" array into individual JSON object strings
    private List<String> splitObjects(String json, String arrayKey) {
        List<String> items = new ArrayList<>();
        String search = "\"" + arrayKey + "\":[";
        int start = json.indexOf(search);
        if (start == -1) return items;
        start += search.length();

        int depth = 0;
        int objStart = -1;
        for (int i = start; i < json.length(); i++) {
            char c = json.charAt(i);
            if (c == '{') {
                if (depth == 0) objStart = i;
                depth++;
            } else if (c == '}') {
                depth--;
                if (depth == 0 && objStart != -1) {
                    items.add(json.substring(objStart, i + 1));
                    objStart = -1;
                }
            } else if (c == ']' && depth == 0) {
                break;
            }
        }
        return items;
    }

    private String fetchUrl(String urlStr) throws Exception {
        URL url = new URL(urlStr);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        conn.setConnectTimeout(5000);
        conn.setReadTimeout(5000);
        BufferedReader br = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        StringBuilder sb = new StringBuilder(4096);
        String line;
        while ((line = br.readLine()) != null) sb.append(line);
        br.close();
        conn.disconnect();
        return sb.toString();
    }

    public static void main(String[] args) throws Exception {
        LongestEvent le = new LongestEvent();
        String result = le.longestDuration("empower integrated markets", "Reggae");
        System.out.println(result);
        result = le.longestDuration("seize out-of-the-box e-commerce", "Blues");
        System.out.println(result);
    }
}