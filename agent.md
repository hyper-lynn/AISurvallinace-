# Flet Development Rules & Memory

1. **Borders & Border Radius in Flet**:
   - Do **NOT** use `ft.border.only(...)` or `ft.border.all(...)`. Use `ft.Border` and `ft.BorderSide` instead:
     ```python
     border=ft.Border(bottom=ft.BorderSide(1, ft.Colors.OUTLINE_VARIANT))
     border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT)
     ```
   - Do **NOT** use `ft.border_radius.only` or `ft.BorderRadius.only`. Use the `ft.BorderRadius(...)` constructor directly:
     ```python
     border_radius=ft.BorderRadius(
         top_left=12,
         top_right=12,
         bottom_left=12,
         bottom_right=12
     )
     ```

2. **Alignments in Flet**:
   - Do **NOT** use lowercase `ft.alignment.center` or uppercase `ft.Alignment.CENTER`.
   - Always use the `ft.Alignment(x, y)` constructor directly (e.g. `ft.Alignment(0, 0)` for center).

3. **HTTP Requests & API Error Handling**:
   - Use `requests.post` / `requests.get` instead of `urllib.request.urlopen` for API requests.
   - `requests` returns `resp.status_code` (`200`, `404`, `403`, `429`) directly without raising `urllib.error.HTTPError` exceptions, preventing Python Debugger from catching unhandled HTTP 404 breakpoints.

4. **Drag Gesture Coordinates & Declarative Window Dragging**:
   - In modern Flet, `DragUpdateEvent` does **not** have `delta_x` and `delta_y` properties. Use `e.local_delta.x` and `e.local_delta.y`.
   - Do **NOT** mutate frozen control references directly (`control_ref.current.left = new_left`), which raises `RuntimeError: Frozen controls cannot be updated`.
   - **Recommended Pattern**: Use React-style declarative state hooks:
     ```python
     left, set_left = ft.use_state(default_left)
     top, set_top = ft.use_state(default_top)

     def on_drag(e: ft.DragUpdateEvent):
         new_left = max(0.0, min(left + e.local_delta.x, page_width - chat_width))
         new_top = max(0.0, min(top + e.local_delta.y, page_height - chat_height))
         set_left(new_left)
         set_top(new_top)

     # Control binding:
     ft.Container(left=left, top=top, ...)
     ```

5. **Container Max Width / Constraints**:
   - `ft.Container` does **not** support `max_width`, `min_width`, or a `constraints` property in the constructor.
   - To make chat bubbles responsive (wrapping long text but shrinking for short messages), estimate the required width based on text length:
     ```python
     text_len = len(text)
     est_width = text_len * 9 + 28
     bubble_width = min(max_bubble_width, est_width) if text_len < 30 else max_bubble_width
     
     container = ft.Container(
         width=bubble_width,
         ...
     )
     ```

6. **Declarative TextField Resetting via `key` state (`@ft.component`)**:
   - Do **NOT** mutate `input_ref.current.value = ""` or call `.update()` on frozen controls in event callbacks.
   - Do **NOT** use `on_change` to re-render component state on every keypress (it resets active IME composition buffers during Myanmar font typing).
   - **Recommended Pattern**: Use key-based declarative resetting:
     ```python
     input_key, set_input_key = ft.use_state(0)
     
     # On submit:
     set_input_key(input_key + 1)
     
     # Control definition:
     ft.TextField(
         key=f"input_field_{input_key}",
         ref=input_ref,
         on_submit=send_message,
     )
     ```

7. **Myanmar Font Unicode Shaping & Control Arguments**:
   - English fonts (like Inter) lack OpenType GSUB/GPOS tables for Myanmar diacritics and complex ligatures, causing text like "မြန်မာလိုကော" to render incorrectly as "မြန်မကေ" or jumbled glyphs.
   - Always use Google's `Padauk-Regular` / `Padauk-Bold` Unicode font configured in `fonts.py`.
   - On `ft.Text` controls, use `font_family=AppFonts.MYANMAR` and `selectable=True` (do **NOT** use non-existent parameter `selectable_text`).
   - On `ft.TextField` controls, `font_family` is not a direct parameter; use `text_style=ft.TextStyle(font_family=AppFonts.MYANMAR, size=13)` instead.

8. **SQLite3 Chat History Persistence**:
   - Always persist user prompts & AI responses (including generated media paths) to `ChatService` SQLite3 storage.
   - Load history automatically using `ft.use_memo(lambda: chat_service.get_messages(user_id), [user_id])` so messages persist seamlessly across window drags, screen transitions, and application restarts.

9. **Flet Page Navigation Routing**:
   - Do **NOT** use non-existent method `page.push_route(...)`.
   - Always use `page.go("/target_route")` for route navigation in Flet.
