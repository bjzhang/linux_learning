import openai
import prompt_toolkit

# Authenticate with OpenAI API using your API key
openai.api_key = "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"

# Set up LangChain model ID
model_id = "gpt-4"

# Define the function to interact with the model and print its responses
def interact(prompt):
    try:
        response = openai.Completion.create(
            engine=model_id,
            prompt=prompt,
            max_tokens=1024,
            n=1,
            stop=None,
            temperature=0.5,
        )
        message = response.choices[0].text
        print(message)
    except Exception as e:
        print(e)

# Start chatting with LangChain
print("Welcome to LangChain. Please type your message:")
while True:
    user_input = prompt_toolkit.prompt("> ")
    interact(user_input)

