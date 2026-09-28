export async function aggregateSamples(samples) {
  const response = await fetch("/api/diagnostics/aggregate", {
    method: "POST", headers: { "Content-Type": "application/json" },
    body: JSON.stringify(samples),
  });
  if (!response.ok) throw new Error("Aggregation failed");
  return response.json();
}
