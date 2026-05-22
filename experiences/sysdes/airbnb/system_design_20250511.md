# Airbnb — System Design Round (Onsite)
**Date**: May 11, 2025  
**Role**: Senior Software Engineer  
**Duration**: ~45 min  
**Format**: System design — data ingestion + query system  
**Status**: Solid Hire  
**Confidence**: 7/10  

---

## Problem: Central Weather Tracking Service

Design a central weather tracking service with the following constraints:

### Data Ingestion
- Weather stations across the country send data points daily
- Legacy Fortran code on each station reads from remote sensors and dumps data into CSV files
- CSV format:
  - Line 1: That day's actual weather data
  - Lines 2–11: 10-day forecast data
- Data needs to be ingested centrally from all stations

### Query Requirements
- Support queries on weather data at **any granularity**:
  - By **station** (single weather station)
  - By **region** (group of stations)
  - By **local area**
  - By **GeoJSON** (arbitrary geographic polygon)
- Must support queries over **up to 30 years** of historical data
- Any data point should be queryable (temperature, humidity, precipitation, etc.)

---

## My Approach

### 0. Clarifying Questions
- **Push vs Pull model** for weather data? → Push model (stations push data)
- **Staleness vs non-staleness** (real-time vs eventual)? 
- **Availability vs Consistency**?
- **Scale**? → "Don't worry about scale, think of any scale. I'll ask if needed."
- Queries need to support both **actual data** and **predicted/forecast data**
- Separated into two tables: **actual** and **predicted** — can join at query time from TimescaleDB

### 1. Stated Structure Upfront
- Told interviewer: "I'll structure my answer starting with core entities, API contract, high-level design, then deep dive. I'll start with a basic design anticipating small scale, and we can evolve."
- Interviewer agreed: "Yeah, sure."
- This was a **deliberate choice** — knew TimescaleDB was the right answer but consciously started with Postgres to show iterative evolution

### 2. High-Level Architecture
- Proposed two main services: **Ingestion Service** and **Read/Query Service**
- Defined core entities and a basic schema
- Defined API contracts (POST for ingestion, GET for queries)

### 3. API Contract — Interviewer Pushback
- Initially missed granularity/data point fields (region, station, etc.) in the GET contract
- Interviewer asked: "Why is the granularity and data point like region not in the contract?"
- Fixed it — added region/station/area to query params
- Also added pagination: `pageSize`, `pageNumber`, `pageIndex` in the GET call

### 4. Data Ingestion — Local to Central
- CSV files on local systems organized in folder structure: each folder = one station, subfolders have day-wise CSVs
- A **batch job** reads from local folders and writes to Postgres (central DB)
- Interviewer asked: "What about entries that are missed?"
- Proposed: keep a small **local DB** to track which entries have been synced to the central table
  - Batch job checks for holes by comparing local DB with remote table
  - Retries missed entries

### 5. Interviewer: "Is there a better way?" (Following the stated plan)
- This was the interviewer moving to the next phase of **my stated structure**, not a nudge
- Proposed decoupling the write path with **Kafka** between the ingestion service and the DB
- **Apache Spark** workers read from Kafka as a consumer group
- Kafka topic: partitioned by **station**, sub-partitioned by **sub-area or day**
- Each Spark worker = dedicated consumer in a consumer group, processes one partition
- This gives fault tolerance, replay-ability, and decoupled ingestion from storage

### 6. Storage Evolution — Postgres → TimescaleDB (Deliberate)
- Did math on peak read load → demonstrated Postgres won't handle it
- Evolved to **TimescaleDB** — this was the **planned evolution**, not a course correction
- Already knew TimescaleDB was the right choice; started with Postgres intentionally to show iterative design
- **Primary key**: composite key of (station_id, date)
- Discussed TimescaleDB features: hypertable partitioning, time chunks, good compression, efficient data encoding
- Added **Redis** cache to serve popular/hot region queries

### 7. Rollup Strategy for Historical Queries
- Added a **rollup job** that pulls from TimescaleDB and pre-aggregates into weekly, monthly, yearly data
- This supports efficient queries over 30 years of history without scanning raw daily data

### 8. Region-Wise Aggregation
- Realized queries can be at any granularity: country, state, district, region
- Raw data is per-station, but queries need region-wise results
- Proposed: the **Spark jobs** that write to TimescaleDB are also sharded by aggregation type:
  - One job for region-wise averages
  - One job for district-wise averages
  - One job for state-wise averages
  - One job for country-wise averages
- Considered alternatives:
  - Offline batch rollup (viable but chose the Spark approach)
  - Compute region-wise rollups at **query time** — explained this would be too slow for large time ranges

### 9. GeoJSON Queries
- Proposed using **PostGIS** (Postgres spatial extension) for GeoJSON polygon queries
- Flow: take the GeoJSON polygon → query PostGIS to find all stations **within** the polygon → return the average of those stations' data
- **Interviewer question**: "What if a query is sent for a GeoJSON region where data doesn't exist?"
- **My answer**: Use PostGIS **KD-tree based** nearest-neighbor query to find nearby regions/stations, return the average data of those nearby stations as an approximation

### 10. Capacity Math & Extras
- Did math on Kafka sizing and auto-scaling of the ingestion service
- Proposed dumping Kafka data to **S3** for future compliance/audit needs
- Interviewer was not much interested in this part — didn't dig deeper

---

## Key Design Decisions

- **Data model**: Separate tables for actual vs predicted data, joined at query time
- **Storage**: Postgres → TimescaleDB (time-series optimized)
- **Primary key**: Composite (station_id, date)
- **Caching**: Redis for popular region queries
- **Ingestion pipeline**: Batch job → Kafka → Spark → TimescaleDB
- **Rollups**: Separate job for weekly/monthly/yearly aggregation
- **Region aggregation**: Spark jobs sharded by granularity level
- **Geo queries**: PostGIS for spatial polygon lookups, KD-tree for nearest-neighbor fallback
- **Missed data handling**: Local tracking DB + hole detection
- **Kafka partitioning**: By station, sub-partitioned by area/day
- **Compliance**: Kafka → S3 dump for audit
- **API pagination**: pageSize, pageNumber, pageIndex

---

## Interviewer Feedback / Interaction

- Caught the missing granularity in API contract — I fixed it promptly (only genuine miss)
- "Is there a better way?" was following my stated plan, not a nudge — I had pre-framed the iterative approach
- Not interested in capacity math / Kafka sizing / S3 compliance details — spent time there that could've been used elsewhere
- Engaged on the GeoJSON edge case (missing data for a polygon) — seemed satisfied with KD-tree nearest-neighbor answer

---

## Reflection

- **What went well**: 
  - Set structure upfront and followed it — interviewer agreed to the plan
  - Deliberate iterative evolution (Postgres → TimescaleDB) showed design maturity
  - Good clarifying questions (push/pull, staleness, availability, actual vs predicted)
  - Covered full breadth: ingestion → storage → caching → aggregation → geo queries
  - Handled edge cases well (missed data, empty GeoJSON, actual vs predicted separation)
  - Correct technology choices with reasoning at each step
- **What could have been stronger**: 
  - API contract initially missed granularity — only genuine miss, should have been there from the start
  - Spent time on capacity math / S3 compliance that interviewer didn't care about — wasted time that could've been used for deeper discussion elsewhere

---

## Pipeline Status

| Round | Type | Status |
|-------|------|--------|
| 1 | Coding (Technical Screen) | ✅ Hire |
| 2 | Coding (Onsite) | ❌ No Hire (likely) |
| 3 | System Design | ✅ Solid Hire |
| 4 | Project Discussion / Cross-functional | Upcoming |

---

## Reflection

*(Fill in after recollecting more details)*
