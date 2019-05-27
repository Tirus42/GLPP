#pragma once

#include "OpenGL++/GL3Types.h"

namespace GLPP {

enum QueryType {
	QT_SAMPLES_PASSED = GL_SAMPLES_PASSED,
	QT_ANY_SAMPLES_PASSED = GL_ANY_SAMPLES_PASSED,
	QT_ANY_SAMPLES_PASSED_CONSERVATIVE = GL_ANY_SAMPLES_PASSED_CONSERVATIVE,
	QT_PRIMITIVES_GENERATED = GL_PRIMITIVES_GENERATED,
	QT_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
	QT_TIME_ELAPSED = GL_TIME_ELAPSED
};

class OpenGLQuery {
	private:
		GLuint query;
		QueryType type;

	public:
		OpenGLQuery(QueryType type) : query(0), type(type) {
			glGenQueries(1, &query);
		}

		~OpenGLQuery() {
			glDeleteQueries(1, &query);
		}

		void beginQuery() {
			glBeginQuery(GLenum(type), query);
		}

		void endQuery() {
			glEndQuery(GLenum(type));
		}

		/// Asks OpenGL if the query is already complete and the result can be retrieved
		bool isResultAvailable() const {
			GLuint result;
			glGetQueryObjectuiv(query, GL_QUERY_RESULT_AVAILABLE, &result);
			return result;
		}

		/// Retrieve query result as int32. May stall the GPU if not finished yet.
		int32_t getQueryResultI32() const {
			int32_t result;
			glGetQueryObjectiv(query, GL_QUERY_RESULT, &result);
			return result;
		}

		/// Retrieve query result as uint32. May stall the GPU if not finished yet.
		uint32_t getQueryResultU32() const {
			uint32_t result;
			glGetQueryObjectuiv(query, GL_QUERY_RESULT, &result);
			return result;
		}

		/// Retrieve query result as int64. May stall the GPU if not finished yet.
		int64_t getQueryResultI64() const {
			int64_t result;
			glGetQueryObjecti64v(query, GL_QUERY_RESULT, &result);
			return result;
		}

		/// Retrieve query result as uint64. May stall the GPU if not finished yet.
		uint64_t getQueryResultU64() const {
			uint64_t result;
			glGetQueryObjectui64v(query, GL_QUERY_RESULT, &result);
			return result;
		}
};

}
