export async function summarizeShards(samples) {
  const response = await fetch("/api/diagnostics/summarize", { method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify(samples) });
  if (!response.ok) throw new Error("Could not summarize shard metrics");
  return response.json();
}
