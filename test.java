import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;


class Result {


        public static List<Integer> awardTopKHotels(String positiveKeywords, String negativeKeywords, List<Integer> hotelIds, List<String> reviews, int k) {
        Set<String> positive = new HashSet<>();
        Set<String> negative = new HashSet<>();
        for (String word : positiveKeywords.split(" "))
            positive.add(word.toLowerCase());
        for (String word : negativeKeywords.split(" "))
            negative.add(word.toLowerCase());

        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < hotelIds.size(); i++) {
            int hotel = hotelIds.get(i);
            int score = map.getOrDefault(hotel, 0);           // BUG 1: was `i`, must be `hotel`
            List<String> review = Arrays.asList(reviews.get(i).split(" "));
            int pos = 0, neg = 0;
            for (String word : review) {
                word = word.replaceAll("[^a-zA-Z]", "").toLowerCase();
                if (positive.contains(word)) pos++;
                if (negative.contains(word)) neg++;
            }
            map.put(hotel, score + pos * 3 - neg);
        }

        // Min-heap of size k: evict lowest score (tie: evict larger ID)
        PriorityQueue<Map.Entry<Integer, Integer>> pq = new PriorityQueue<>(
            (a, b) -> a.getValue().equals(b.getValue())       // BUG 2: was `==`, must be `.equals()`
                ? b.getKey().compareTo(a.getKey())
                : a.getValue() - b.getValue());

        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            pq.offer(entry);
            if (pq.size() > k)
                pq.poll();
        }

        List<Integer> result = new ArrayList<>();
        while (!pq.isEmpty()) {
            result.add(0, pq.poll().getKey());
        }
        return result;
    }

    public static void main(String[] args) {
        // Test case: 3 hotels, 2 positive words, 1 negative word, top 2
        String pos = "breakfast beach citycenter location metro view staff price";
        String neg = "not";
        List<Integer> hotelIds = Arrays.asList(1,2,1,1,2);
        List<String> reviews = Arrays.asList(
            "This hotel has a nice view of the citycenter. The location is perfect.",          // hotel 1: clean(+3) beautiful(+3) = 6
            "The breakfast is ok. Regarding location, it is quite far from citycenter but price is cheap so it is worth.",
            "Location is excellent, 5 minutes from citycenter. There is also a metro station very close to the hotel.",
            "They said I couldn't take my dog and there were other guests with dogs! That is not fair.",
            "Very friendly staff and good cost-benefit ratio. Its location is a bit far from citycenter."                   // hotel 1: noisy(-1) clean(+3) = +2, total=8
        );
        int k = 2;

        List<Integer> result = awardTopKHotels(pos, neg, hotelIds, reviews, k);
        System.out.println("Top " + k + " hotels: " + result); // expect [3, 1]
    }
}