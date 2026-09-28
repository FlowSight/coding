export async function maximumInvitations(grid) {
  const response = await fetch("/api/invitations/maximum", { method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify({ grid }) });
  if (!response.ok) throw new Error("Matching request failed");
  return (await response.json()).count;
}
