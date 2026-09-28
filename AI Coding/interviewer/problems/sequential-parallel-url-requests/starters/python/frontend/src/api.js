export async function runRequests(urls) {
  const response = await fetch("/api/requests/run", {
    method: "POST", headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ urls }),
  });
  if (!response.ok) throw new Error("Request batch failed");
  return response.json();
}
