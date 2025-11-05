Project Title: QuantDuel — Scalable 1v1 Real-Time Code Duel Platform
Objective: Build a full-stack, production-grade web app for live 1v1 programming duels, featuring real-time code synchronization, secure code execution, leaderboards, matchmaking, and scalable infrastructure.

💡 Vision

QuantDuel enables two users to compete live by solving coding problems head-to-head.
Each user sees a shared synchronized editor (like VS Code), submits solutions, and receives verdicts instantly (Accepted, Wrong Answer, etc.) from an isolated sandbox environment (Judge0).

The platform must be fast, scalable, reliable, and industry-grade, capable of supporting thousands of concurrent duels with strong observability and secure backend execution.

🧩 Tech Stack

Frontend:

Framework: Next.js (TypeScript, App Router)

Styling: TailwindCSS + Shadcn/UI

State: Zustand / React Query

Editor: Monaco Editor (VS Code-like experience)

Realtime: Socket.IO client

Deployment: Vercel

Backend:

Framework: NestJS (TypeScript)

API: REST + WebSocket Gateway

Realtime: Socket.IO (Redis adapter)

Queue system: BullMQ (Redis-backed)

Code Execution: Judge0 API (self-hosted or cloud)

DB: PostgreSQL

Cache/Queue: Redis

ORM: Prisma

Auth: JWT or Clerk/Auth0

Deployment: Render / Railway / AWS ECS

Worker:

Node.js TypeScript worker using BullMQ to handle Judge jobs asynchronously

Communicates with backend over Redis and Postgres

Infra / CI/CD:

Docker for each service

docker-compose.yml for local dev

GitHub Actions for test/build/deploy

Sentry for monitoring

Prometheus + Grafana for metrics

Terraform (optional) for infra provisioning

🏗️ Directory Structure
quant-duel/
├── package.json
├── pnpm-workspace.yaml
├── tsconfig.json
├── docker-compose.yml
├── .env.example
├── .gitignore
├── README.md
│
├── packages/
│   ├── frontend/          # Next.js app
│   │   ├── src/
│   │   │   ├── pages/
│   │   │   ├── components/
│   │   │   ├── hooks/
│   │   │   ├── lib/
│   │   │   └── styles/
│   │   ├── public/
│   │   ├── package.json
│   │   └── tsconfig.json
│   │
│   ├── backend/           # NestJS API + WebSocket
│   │   ├── src/
│   │   │   ├── main.ts
│   │   │   ├── app.module.ts
│   │   │   ├── modules/
│   │   │   │   ├── auth/
│   │   │   │   ├── duel/
│   │   │   │   ├── user/
│   │   │   │   └── judge/
│   │   │   ├── websocket/
│   │   │   │   └── gateway.ts
│   │   │   └── common/
│   │   │       ├── dto/
│   │   │       ├── entities/
│   │   │       └── utils/
│   │   ├── package.json
│   │   └── tsconfig.json
│   │
│   ├── worker/            # BullMQ worker
│   │   ├── src/
│   │   │   ├── main.ts
│   │   │   └── jobs/judge-job.ts
│   │   ├── package.json
│   │   └── tsconfig.json
│   │
│   └── shared/            # Shared types & utils
│       ├── src/
│       │   ├── types.ts
│       │   ├── constants.ts
│       │   └── utils.ts
│       ├── package.json
│       └── tsconfig.json
│
└── infra/
    ├── Dockerfile.frontend
    ├── Dockerfile.backend
    ├── Dockerfile.worker
    └── terraform/

⚙️ Environment Setup

Services required locally:

Redis (for pub/sub, BullMQ)

PostgreSQL

Judge0 (optional for self-hosted)

All defined via docker-compose.yml

Environment Variables:

DATABASE_URL=postgresql://postgres:password@postgres:5432/quantduel
REDIS_URL=redis://redis:6379
JUDGE0_URL=https://api.judge0.com
JWT_SECRET=supersecretkey
NEXT_PUBLIC_BACKEND_URL=http://localhost:4000
NEXT_PUBLIC_WS_URL=ws://localhost:4000

🧠 Core Functional Modules
1. Authentication

Signup/Login via JWT or OAuth (Clerk/Auth0)

Protect duel routes

Store users in Postgres (users table)

2. Duel System

User can create a duel, generate a match ID, and share it.

Another user joins via ID.

Backend initializes a WebSocket room for both players.

Both share the same code buffer (real-time sync).

Countdown timer + problem statement displayed.

First to submit correct code wins the duel.

3. Realtime Collaboration

Implement using Socket.IO

Events: join_room, code_change, submit_code, judge_result, end_match

Redis adapter enables horizontal scaling of WebSocket servers.

4. Code Execution / Judging

Player submits -> backend queues submission -> worker sends code to Judge0 API.

Worker polls Judge0 for result → sends back verdict to backend → emits via Socket.IO.

5. Leaderboard & History

Store duels in Postgres

Maintain leaderboard by win count / accuracy / avg solve time

6. Admin Panel (Optional)

Create new coding problems

View system metrics (jobs, duels, errors)

🚀 Scalability / Deployment Plan

Frontend: Deploy on Vercel (auto CI from packages/frontend)

Backend: Deploy on Render / Railway / ECS

Worker: Deploy on ECS or as Render background service

Redis + Postgres: Managed (Upstash, Supabase, or AWS RDS)

Judge0: Cloud or private container (behind Nginx proxy)

CI/CD: GitHub Actions

Test → Build → Lint → Deploy

Monitoring: Sentry for exceptions, Prometheus for metrics

🧱 Database Schema (Simplified)
users (
  id UUID PRIMARY KEY,
  username TEXT UNIQUE,
  email TEXT UNIQUE,
  password_hash TEXT,
  rating INT DEFAULT 1500
)

problems (
  id UUID PRIMARY KEY,
  title TEXT,
  description TEXT,
  difficulty TEXT,
  input_format TEXT,
  output_format TEXT,
  sample_input TEXT,
  sample_output TEXT,
  test_cases JSONB
)

duels (
  id UUID PRIMARY KEY,
  player1 UUID REFERENCES users(id),
  player2 UUID REFERENCES users(id),
  problem_id UUID REFERENCES problems(id),
  winner UUID REFERENCES users(id),
  created_at TIMESTAMP DEFAULT now(),
  ended_at TIMESTAMP
)

🧰 Tools / Libraries
Purpose	Library
Editor	@monaco-editor/react
Realtime	socket.io, socket.io-client, @nestjs/websockets
Queue	bullmq
ORM	prisma
DB	postgresql
Auth	jsonwebtoken, bcrypt, or clerk
Monitoring	@sentry/node, @sentry/nextjs
UI	tailwindcss, shadcn/ui, framer-motion
📦 Milestones

M1 — Local MVP

Backend REST + WebSocket up

Frontend editor + duel page working

Judge0 integrated locally

Auth + DB persistence

M2 — Production Ready

Redis adapter for WebSocket

CI/CD pipelines

Leaderboard + metrics

Cloud deployment

M3 — Scaling & Monitoring

Add tracing, Sentry, dashboards

Optimize Redis + DB connections

Add problem management admin

🧑‍💻 Cursor AI Tasks

Cursor should:

Scaffold this full directory structure.

Generate Dockerfiles and docker-compose.yml for local stack.

Set up Next.js (frontend) and NestJS (backend) with sample endpoints.

Add WebSocket gateway for duels (echo test first).

Implement Monaco Editor in frontend with Socket.IO integration.

Add Judge0 client module (backend + worker).

Configure Prisma ORM and create DB schema.

Write CI workflow for GitHub Actions (build/test).

Deploy preview-ready frontend/backend using Render or Vercel.

Generate minimal README with setup + contribution instructions.

🧭 Quality Expectations

Modular, maintainable code structure

Full TypeScript typing

ESLint + Prettier configured

0 lint errors, 0 build errors

Secure (no eval, sandbox only)

Fast local dev via Docker

Documented environment setup

🧱 Deliverables

✅ Complete monorepo (Next.js + NestJS + Worker + Shared)
✅ Dockerized setup (Postgres, Redis, Judge0)
✅ Realtime duel (Socket.IO)
✅ Judge0 integration (async verdicts)
✅ CI/CD pipeline
✅ Production deployment ready

🧭 Tags / Keywords

TypeScript, Next.js, NestJS, BullMQ, Socket.IO, Judge0, PostgreSQL, Redis, Monaco Editor, Docker, Vercel, Render, CI/CD, Sentry, Prisma, Full Stack, Realtime Collaboration, Competitive Programming, Microservices, Infra as Code, Scalable System Design