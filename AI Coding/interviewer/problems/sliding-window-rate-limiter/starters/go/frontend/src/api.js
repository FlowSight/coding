export async function requestDecision(at) {
  const response = await fetch("/api/limiter/allow", { method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify({ at }) });
  if (!response.ok) throw new Error("Limiter decision failed");
  return (await response.json()).allowed;
}
