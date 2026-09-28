export async function calculateMaximum(grid) {
  const response = await fetch("/api/invitations/maximum", {
    method: "POST", headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ grid }),
  });
  if (!response.ok) throw new Error("Matching failed");
  return response.json();
}
