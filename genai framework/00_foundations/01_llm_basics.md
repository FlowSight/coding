# LLM Basics - How Large Language Models Work

## 1. What is an LLM?

A Large Language Model is a neural network trained on massive text corpora to predict the next token in a sequence. Despite the simple objective, this produces emergent capabilities: reasoning, code generation, summarization, etc.

**Key models to know:**
- GPT-4/4o (OpenAI) - closed source, best general purpose
- Claude (Anthropic) - closed source, strong reasoning
- Llama 3 (Meta) - open weights, various sizes (8B, 70B, 405B)
- Gemini (Google) - multimodal native
- Mistral/Mixtral - open, efficient MoE architecture

## 2. Transformer Architecture (High Level)

```
Input Text → Tokenizer → Embeddings → [Transformer Blocks × N] → Output Probabilities
```

### Core Components:
1. **Self-Attention**: Each token attends to all other tokens. Computes Q, K, V matrices.
   - Attention(Q,K,V) = softmax(QK^T / √d_k) × V
   - Multi-head attention: multiple attention heads capture different relationships
   
2. **Feed-Forward Network**: Position-wise MLP after attention layer

3. **Layer Normalization**: Stabilizes training

4. **Positional Encoding**: Since attention is permutation-invariant, positions are encoded
   - Original: sinusoidal
   - Modern: RoPE (Rotary Position Embeddings) - enables length extrapolation

### Key Parameters:
- **d_model**: Hidden dimension (e.g., 4096 for GPT-3)
- **n_layers**: Number of transformer blocks (96 for GPT-3)
- **n_heads**: Number of attention heads (96 for GPT-3)
- **Context window**: Max tokens in one pass (128K for GPT-4, 200K for Claude)

## 3. Training Pipeline

```
Stage 1: Pre-training (next token prediction on internet text)
    ↓
Stage 2: Supervised Fine-Tuning (SFT on instruction-response pairs)
    ↓
Stage 3: RLHF / DPO (alignment with human preferences)
```

### Pre-training:
- Objective: Minimize cross-entropy loss on next token prediction
- Data: Trillions of tokens from web, books, code
- Cost: Millions of dollars, thousands of GPUs

### Fine-tuning:
- **Full fine-tuning**: Update all weights (expensive)
- **LoRA/QLoRA**: Low-rank adaptation, update small matrices (efficient)
- **Instruction tuning**: Train on (instruction, response) pairs

### Alignment:
- **RLHF**: Train reward model from human preferences, then use PPO
- **DPO**: Direct Preference Optimization (simpler, no reward model needed)
- **Constitutional AI**: Self-critique and revision

## 4. Inference

### Autoregressive Generation:
```
"The capital of France is" → [Model] → "Paris"
                                          ↓ (append and repeat)
"The capital of France is Paris" → [Model] → "."
```

Each forward pass generates ONE token. This is why LLMs are slow for long outputs.

### Decoding Strategies:
- **Greedy**: Always pick highest probability token
- **Temperature**: Scale logits by T. T<1 = more focused, T>1 = more random
- **Top-k**: Only consider top k tokens
- **Top-p (nucleus)**: Consider tokens until cumulative probability ≥ p
- **Beam search**: Maintain k candidate sequences (rarely used for chat)

### Key Performance Metrics:
- **TTFT** (Time to First Token): Latency before first output token
- **Tokens/second**: Generation speed
- **Context window utilization**: Longer context = slower + more expensive

## 5. Scaling Laws

**Chinchilla scaling law**: Optimal model size scales with data size.
- For compute-optimal training: tokens ≈ 20 × parameters
- GPT-3 (175B params) was undertrained by this law

**Emergent abilities**: Some capabilities only appear at scale:
- Chain-of-thought reasoning (~100B+ params)
- In-context learning (few-shot)
- Code generation

## 6. Key Concepts for Interviews

### Context Window
- The "working memory" of the model
- Everything (system prompt + conversation + retrieved docs) must fit
- Cost is O(n²) with attention (mitigated by Flash Attention, paged attention)

### Hallucination
- Models generate plausible but incorrect information
- Mitigation: RAG, grounding, citations, confidence calibration

### In-Context Learning (ICL)
- Models can learn patterns from examples in the prompt
- No weight updates needed
- Works through: few-shot examples, demonstrations

### Knowledge Cutoff
- Models only know what was in training data
- Need external tools/retrieval for current information

## 7. Cost Model (Important for D.E. Shaw)

```
Cost = (Input tokens × input_price) + (Output tokens × output_price)
```

**GPT-4o (June 2024)**: $5/M input, $15/M output
**Claude 3.5 Sonnet**: $3/M input, $15/M output
**Llama 3 70B (self-hosted)**: GPU cost (~$2-4/hr on A100)

### Cost Optimization:
1. Prompt caching (reuse prefix computations)
2. Shorter prompts (remove redundant instructions)
3. Smaller models for simpler tasks (routing)
4. Batch processing (higher throughput, lower per-token cost)
5. Output token limits

## 8. Interview Questions to Expect

1. "Explain how attention works and why it's O(n²)"
2. "What's the difference between pre-training and fine-tuning?"
3. "When would you use a smaller model vs GPT-4?"
4. "How do you handle the context window limit?"
5. "Explain the trade-off between temperature and response quality"
6. "What are the limitations of current LLMs?"

## Key Takeaways

| Concept | One-liner |
|---------|-----------|
| Transformer | Attention mechanism that relates all tokens to each other |
| Autoregressive | Generates one token at a time, left to right |
| Context window | Fixed-size working memory (tokens in = attention cost) |
| Temperature | Controls randomness: 0 = deterministic, 1 = creative |
| RLHF | Aligns model behavior with human preferences |
| Scaling laws | More params + more data = better, but diminishing returns |
| Hallucination | Confident generation of incorrect information |
