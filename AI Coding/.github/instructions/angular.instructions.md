---
applyTo: "**/*.component.ts,**/*.component.html,**/*.component.scss,**/*.module.ts,**/*.service.ts,**/*.html,**/*.css,**/*.scss"
description: "Angular and frontend conventions for UI components. Use when writing, reviewing, or modifying Angular components, templates, styles, or services."
---

# Angular / Frontend Conventions

## Angular
- Standalone components preferred over NgModule-declared components.
- Use Angular signals and `input()`/`output()` over `@Input()`/`@Output()` decorators.
- Reactive forms over template-driven forms.
- Services are `providedIn: 'root'` unless feature-scoped.

## Style
- Naming: `feature-name.component.ts`, `feature-name.service.ts`.
- One component per file. No multi-component files.
- Use `OnPush` change detection strategy by default.

## CSS/SCSS
- Component styles scoped via Angular encapsulation (default ViewEncapsulation).
- Use CSS custom properties (variables) for theming.
- No `!important`. Fix specificity issues properly.
- Mobile-first responsive design with `min-width` breakpoints.
- BEM naming for custom classes: `.block__element--modifier`.

## HTML Templates
- Semantic HTML elements (`<nav>`, `<main>`, `<section>`, `<article>`).
- Always provide `alt` for images, `aria-label` for interactive elements.
- Use `@if`/`@for` control flow (Angular 17+) over `*ngIf`/`*ngFor`.

## Structure
```
src/app/
  core/           # Singleton services, guards, interceptors
  shared/         # Reusable components, directives, pipes
  features/
    feature-name/
      feature-name.component.ts
      feature-name.component.html
      feature-name.component.scss
      feature-name.service.ts
      feature-name.routes.ts
```
