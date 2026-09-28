export async function addRoute(pattern, handler) {
  const response = await fetch("/api/routes", { method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify({ pattern, handler }) });
  if (!response.ok) throw new Error("Could not add route");
}
export async function matchRoute(path) {
  const response = await fetch(`/api/routes/match?path=${encodeURIComponent(path)}`);
  if (!response.ok) throw new Error("Could not match route");
  return response.json();
}
