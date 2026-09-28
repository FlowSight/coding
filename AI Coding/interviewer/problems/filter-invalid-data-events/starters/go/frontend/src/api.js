export async function filterEvents(events) {
  const response = await fetch("/api/events/filter", { method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify(events) });
  if (!response.ok) throw new Error("Event validation failed");
  return response.json();
}
