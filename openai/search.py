#!/usr/bin/env python3
import os
import sys
from langchain.tools import Tool
from langchain.utilities import GoogleSearchAPIWrapper
from openai import OpenAI

question = sys.argv[1]

search = GoogleSearchAPIWrapper()

tool = Tool(
    name="Google Search",
    description="Search Google for recent results.",
    func=search.run,
    num_search_results=5
)

result = tool.run(question)

client = OpenAI()

response = client.chat.completions.create(
    model="gpt-4",
    messages=[
        {"role": "system", "content": "You are a helpful assistant for computer architecture and operating system"},
        {"role": "user", "content": question}
    ]
)

# Print the entire response
print(response)

print("with assistant")
print(result)

response = client.chat.completions.create(
    model="gpt-4",
    messages=[
        {"role": "system", "content": "You are a helpful assistant for computer architecture and operating system"},
        {"role": "assistant", "content": result},
        {"role": "user", "content": question}
    ]
)

# Print the entire response
print(response)

