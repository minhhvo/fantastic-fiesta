
import os
import datetime as datetime
import xml.etree.ElementTree as ET

def parse_report(file_path, title):
    if not os.path.exists(file_path):
        return f"<h3>{title}</h3><p>No report generated yet.</p>"

    try:
        tree = ET.parse(file_path)
        root = tree.getroot()

        # CTest output usually puts testcases directly under a root <testsuite>
        html = f"<h3>{title}</h3><ul>"
        for testcase in root.iter('testcase'):
            name = testcase.get('name', 'Unknown')
            time = testcase.get('time', '0')
            failure = testcase.find('failure')
            status = "Pass" if failure is None else f"Fail: {failure.text}"
            html += f"<li><strong>{status}</strong> | {name} ({time}s)</li>"
        html += "</ul>"
        return html
    except Exception as e:
        return f"<p>Error parsing {title}: {e}</p>"

def build_dashboard():
    os.makedirs("docs", exist_ok=True)

    # 1. Parse Test Reports
    unit_html = parse_report("build/reports/unit_test_report.xml", "Unit Tests")
    bench_html = parse_report("build/reports/benchmark_report.xml", "Micro-Benchmarks")

    # 2. Parse Changelog (if it exists)
    changelog_content = "<p>No CHANGELOG.md found in root.</p>"
    if os.path.exists("CHANGELOG.md"):
        with open("CHANGELOG.md", "r") as f:
            changelog_content = f"<pre style='white-space: pre-wrap;'>{f.read()}</pre>"

    # 3. Generate HTML
    timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    html_template = f"""
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Calculator Project Dashboard</title>
        <style>
            body {{ font-family: system-ui, sans-serif; line-height: 1.6; max-width: 800px; margin: 0 auto; padding: 2rem; color: #333; }}
            h1, h2, h3 {{ color: #111; border-bottom: 1px solid #eaeaea; padding-bottom: 0.5rem; }}
            ul {{ list-style: none; padding: 0; }}
            li {{ padding: 0.5rem 0; border-bottom: 1px solid #f0f0f0; }}
            pre {{ background: #f6f8fa; padding: 1rem; border-radius: 6px; }}
        </style>
    </head>
    <body>
        <h1>Project Dashboard</h1>
        <p><small>Last Updated: {timestamp}</small></p>

        <h2>Latest Test Results</h2>
        {unit_html}
        {bench_html}

        <h2>Changelog</h2>
        {changelog_content}
    </body>
    </html>
    """

    with open("docs/index.html", "w") as f:
        f.write(html_template)
    print("Dashboard generated at docs/index.html")

if __name__ == "__main__":
    build_dashboard()
