export async function attempt(timestamp) {
  const response = await fetch("/api/limiter/attempt", {
    method: "POST", headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ timestamp: timestamp || null }),
  });
  if (!response.ok) throw new Error("Limiter request failed");
  return response.json();
}
